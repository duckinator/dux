COLOR_GREEN = "\\033[0\;32m" # Set console color to green
COLOR_RESET = "\\033[0m"    # Set console color to previously used one

CLEAR_TO_EOL = "\\033[K"    # Clear to end of line

UP_ONE_LINE = "\\033[1A"    # Move cursor up one line

MESSAGE_PRE = "${UP_ONE_LINE}\\r${CLEAR_TO_EOL}"

STATUS = echo -e "${MESSAGE_PRE}${COLOR_GREEN}[$(1)]${COLOR_RESET} $(2)"

