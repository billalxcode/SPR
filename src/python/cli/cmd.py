import time
from src.python.terminal import COLOR_GREEN, COLOR_CYAN, COLOR_WHITE, COLOR_RESET, CONSOLE_NORM
from src.python.cli.command import CommandParser
from src.python.cli.handler import Handler
from src.python.environment import Environment
from src.python.terminal import Console

class CommandLine:
    def __init__(self) -> None:
        self.modules = ""
        self.PROMPT = f"{COLOR_WHITE}[{COLOR_GREEN}#{COLOR_WHITE}] {COLOR_CYAN}_> {COLOR_GREEN}"
        self.environment = Environment()
        self.environment.load_from_files()
        time.sleep(2)
        self.environment.save()

        self.console = Console(self.environment)
        self.parser = CommandParser()
        self.handler = Handler(self.environment)

    def build_prompt(self):
        if self.modules == "":
            return self.PROMPT
        else:
            self.PROMPT = self.PROMPT.replace("#", self.modules)

    def user_input(self):
        self.build_prompt()
        user_input = input(self.PROMPT)
        self.console.print_console(COLOR_RESET, CONSOLE_NORM)
        return user_input

    def run(self):
        self.console.print_info("Running on 'CLI' mode") 
        while True:
            try:
                user_input = self.user_input()
                command = self.parser.parse_command(user_input)
                argument = self.parser.parse_argument(user_input)
                self.handler.handle_command(command, argument)
                if self.handler.module != self.modules:
                    self.modules = self.handler.module
            except KeyboardInterrupt:
                self.console.quit(isUser=True)