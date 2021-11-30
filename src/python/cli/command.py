
class CommandParser:
    def __init__(self) -> None:
        self.PREFIX = "!"
        self.readline = []
        
    def filter_tab(self, string: str = ""):
        string_strip = string.strip()
        if "\t" in string:
            tab_counter = string.count("\t")
            return string_strip, tab_counter
        else:
            return string_strip, 0

    def parse(self, cmd_string: str = ""):
        try:
            isText = False
            string, tab_count = self.filter_tab(cmd_string)             
            cmd_split = string.split(" ")
            command = cmd_split[0]
            if command.startswith(self.PREFIX):
                command = command.replace(self.PREFIX, "")
                isText = False
                try:
                    argument = cmd_split[1:]
                except IndexError:
                    argument = []
                return command.lower(), argument, isText
            else:
                isText = True
                return cmd_string, None, isText

        except IndexError:
            return None, None

    def parse_argument(self, cmd_string: str = ""):
        cmd_, argument, _ = self.parse(cmd_string)
        return argument

    def parse_command(self, cmd_string: str = ""):
        command, argument, _ = self.parse(cmd_string)
        return command
