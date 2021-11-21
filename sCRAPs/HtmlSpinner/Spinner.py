import os

SpinnerHTML = ""
with open(os.path.dirname(os.path.realpath(__file__)).replace("\\", "/") + "/Spinner.html") as f:
    SpinnerHTML = "".join(f.readlines()).replace("\n", "")

class Spinner:
    def GetSpinner(Percentage = 0) -> str:
        TurntSpinner = SpinnerHTML

        Percentage = 0 if Percentage < 0 else 100 if Percentage > 100 else Percentage

        if Percentage <= 50:
            TurntSpinner = TurntSpinner.replace("VISIBILITY PURPLE TOP", "hidden")
            TurntSpinner = TurntSpinner.replace("VISIBILITY WHITE MIDDLE", "visible")
            
            TurntSpinner = TurntSpinner.replace("DEGREES WHITE MIDDLE", str(360 - (round(Percentage/100*360*100)/100)) + "deg")
        else:
            TurntSpinner = TurntSpinner.replace("VISIBILITY PURPLE TOP", "visible")
            TurntSpinner = TurntSpinner.replace("VISIBILITY WHITE MIDDLE", "hidden")

            TurntSpinner = TurntSpinner.replace("DEGREES PURPLE TOP", str(180 - (round(Percentage/100*360*100)/100)) + "deg")

        return TurntSpinner

if __name__ == "__main__":

    from html2image import Html2Image
    hti = Html2Image()
    hti.screenshot(html_str=Spinner.GetSpinner(30), save_as="scrn.png")