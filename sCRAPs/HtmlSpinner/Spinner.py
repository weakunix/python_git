import os

SpinnerHTML = ""
with open(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/") + "/Spinner.html") as f:
    SpinnerHTML = "".join(f.readlines()).replace("\n", "")

class Spinner:
    def GetSpinner(Percentage = 0, Title = "", Subtitle = "") -> str:
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

if __name__ == "__main__":

    from html2image import Html2Image
    from PIL import Image
    
    hti = Html2Image()
    hti.screenshot(html_str=Spinner.GetSpinner(10/50, "10/50", "Hours"), save_as="scrn.png")

    img = Image.open(r"C:\Users\kingo\Documents\GitHub\python_git\scrn.png")
    img = img.crop((0, 0, 150, 150))
    img.save(r"C:\Users\kingo\Documents\GitHub\python_git\sCRAPs\HtmlSpinner\scrn.png")