#!python3

'''
used pythonista 3 example
'''

import appex, ui
import os
from math import ceil, floor

# NOTE: The ROWS variable determines the number of rows in "compact" mode. In expanded mode, the widget shows all shortcuts.
COLS = 1
ROWS = 4

# Each shortcut should be a dict with at least a 'title' and 'url' key. 'color' and 'icon' are optional. If set, 'icon' should be the name of a built-in image.
SHORTCUTS = [
{'title': 'New Email', 'url': 'mailto:', 'color': '#5e96ff', 'icon': 'iow:email_24'},
{'title': 'New Message', 'url': 'sms://', 'color': '#5ec0ff', 'icon': 'iow:chatbox_24'},
{'title': 'Pythonista', 'url': 'pythonista3://', 'color': '#45d3e8', 'icon': 'iow:chevron_right_24'},
{'title': 'Forum', 'url': 'http://forum.omz-software.com', 'color': '#4dd19d'},
{'title': 'Google', 'url': 'http://google.com', 'color': '#a9de31'},
{'title': 'DuckDuckGo', 'url': 'http://duckduckgo.com', 'color': '#ffd026' },
{'title': 'Amazon', 'url': 'http://amazon.com', 'color': '#ff8e13'},
{'title': 'eBay', 'url': 'http://ebay.com', 'color': '#ff4a09'},
]

def shortCut(array):
    global SHORTCUTS
    SHORTCUTS = array 

class LauncherView (ui.View):
    def __init__(self, shortcuts, *args, **kwargs):
        row_height = 110 / ROWS
        super().__init__(self, frame=(0, 0, 300, ceil(len(shortcuts) / COLS) * row_height), *args, **kwargs)
        self.buttons = []
        for s in shortcuts:
            btn = ui.Button(title=' ' + s['title'], image=ui.Image(s.get('icon', 'iow:compass_24')), name=s['url'],
            action=self.button_action, bg_color=s.get('color', '#55bcff'), tint_color='#fff', corner_radius=9)
            self.add_subview(btn)
            self.buttons.append(btn)

    def layout(self):
        bw = self.width / COLS
        bh = floor(self.height / ROWS) if self.height <= 130 else floor(110 / ROWS)
        for i, btn in enumerate(self.buttons):
            btn.frame = ui.Rect(i%COLS * bw, i//COLS * bh, bw, bh).inset(2, 2)
            btn.alpha = 1 if btn.frame.max_y < self.height else 0

    def button_action(self, sender):
        import shortcuts
        shortcuts.open_url(sender.name)

def main():
    widget_name = __file__ + str(os.stat(__file__).st_mtime)
    v = appex.get_widget_view()
    # Optimization: Don't create a new view if the widget already shows the launcher.
    if v is None or v.name != widget_name:
        v = LauncherView(SHORTCUTS)
        v.name = widget_name
        appex.set_widget_view(v)

if __name__ == '__main__':
    main()    
