COLOR_GREEN  = "\\033[0\;32m" # Set console color to green
COLOR_RED    = "\\033[0\;31m" # Set console color to red
COLOR_BLUE   = "\\033[0\;34m" # Set console color to blue
COLOR_RESET  = "\\033[0m"    # Set console color to previously used one

STATUS       = printf "${COLOR_GREEN}\\b["$1"]${COLOR_RESET} $(dir $(2))${COLOR_RED}\\b$(notdir $(2))${COLOR_RESET}\r\n"

