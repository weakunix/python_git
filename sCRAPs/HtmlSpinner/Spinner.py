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

        FileName = f"""/FinalSpinners/Percents/{int(Percentage*100)}.png"""

        SavedPath = "/".join(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/").split("/")) + FileName

        if os.path.exists(SavedPath):
            return

        HTML = Spinner.GetSpinnerHTML(Percentage, Title, Subtitle)

        HTI.screenshot(html_str=HTML, save_as="tmp.png")

        GeneratedImage = Image.open("tmp.png")
        GeneratedImage = GeneratedImage.crop((0, 0, 150, 150))
        GeneratedImage.save(SavedPath)

        return SavedPath

def CalculateLetterGrade(Points):

  if int(Points) >= 100:
    return "A+"
  
  if len(Points) == 1:
    Points = "0" + Points
  
  Grade = ["A", "A", "B", "C", "D", "F", "F", "F", "F", "F", "F"]
  Modifers = ["-" for _ in range(3)] + ["" for _ in range(4)] + ["+" for _ in range(3)]
  
  Result = Grade[10 - int(Points[0])] + (Modifers[int(Points[1])] if int(Points[0]) >= 6 else "")

  return Result

if __name__ == "__main__":

    for i in range(101):
        Spinner.GetSpinnerImage(i/100, f"{i}%", CalculateLetterGrade(str(i)))
