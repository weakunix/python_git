import os
from html2image import Html2Image
from PIL import Image

SpinnerHTML = ""
with open(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/") + "/Spinner.html") as f:
    SpinnerHTML = "".join(f.readlines()).replace("\n", "")

HTI = Html2Image()

class Spinner:
    def GetSpinnerHTML(Percentage = 0, Title = "", Subtitle = "") -> str:
        TurntSpinner = SpinnerHTML

        if Percentage < 1 and Percentage > 0:
            Percentage = Percentage * 100

        Percentage = 0 if Percentage < 0 else 100 if Percentage > 100 else Percentage

        if Percentage <= 50:
            TurntSpinner = TurntSpinner.replace("VISIBILITY PURPLE TOP", "hidden")
            TurntSpinner = TurntSpinner.replace("VISIBILITY WHITE MIDDLE", "visible")
            
            TurntSpinner = TurntSpinner.replace("DEGREES WHITE MIDDLE", str(360 - (round(Percentage/100*360*100)/100)) + "deg")
        else:
            TurntSpinner = TurntSpinner.replace("VISIBILITY PURPLE TOP", "visible")
            TurntSpinner = TurntSpinner.replace("VISIBILITY WHITE MIDDLE", "hidden")

            TurntSpinner = TurntSpinner.replace("DEGREES PURPLE TOP", str(180 - (round(Percentage/100*360*100)/100)) + "deg")
        
        TurntSpinner = TurntSpinner.replace("TITLE", str(Title))
        TurntSpinner = TurntSpinner.replace("SUBTTL", str(Subtitle))

        return TurntSpinner

    def GetSpinnerImage(Percentage = 0, Title = "", Subtitle = "") -> str:

        FileName = f"""/FinalSpinners/{Title.split("/")[1]}/{Subtitle.replace(" ", "_") + "_" + Title.replace("/", "_")}.png"""

        SavedPath = "/".join(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/").split("/")) + FileName

        if os.path.exists(SavedPath):
            return

        HTML = Spinner.GetSpinnerHTML(Percentage, Title, Subtitle)

        HTI.screenshot(html_str=HTML, save_as="tmp.png")

        GeneratedImage = Image.open("tmp.png")
        GeneratedImage = GeneratedImage.crop((0, 0, 150, 150))
        GeneratedImage.save(SavedPath)

        return SavedPath

if __name__ == "__main__":

    for i in range(5 + 1):
        Equation = f"{i}/{5}"
        Spinner.GetSpinnerImage(eval(Equation) * 100, Equation, "Outside Hours")
    
    for x in range(3):

        ran = [10, 50, 250][x]

        for i in range(ran + 1):
            Equation = f"{i}/{ran}"

            Spinner.GetSpinnerImage(eval(Equation) * 100, Equation, "Hours")