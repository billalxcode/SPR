from src.python.environment import Environment
from src.python.terminal import CONSOLE_NORM, Console
from src.python.cli.helper import command_helper, command_use_helper
from src.python.utils import Data
from src.python.utils import isDigit

class Handler:
    def __init__(self, environments: Environment) -> None:
        self.environment = environments

        self.console = Console(self.environment)
        self.module = ""
        
    def build_default_environments(self):
        self.environment.create("port", "", False)
        self.environment.create("baudrate", 9600, False)

    def handle_command_use(self, argument: list = []):
        try:
            argument_length = len(argument)
            if argument_length == 1:
                use_type = argument[0]
                if use_type == "lcd":
                    self.module = use_type
            else:
                self.console.print_error("You are only allowed to use one module")
        except IndexError:
            self.console.print_error(f"'module' argument required")
            return False

    def handle_command_show(self, argument: list = []):
        try:
            argument_length = len(argument)
            if argument_length == 1:
                key = argument[0]
                value = self.environment.select(key)
                if value != False:
                    value = str(value)
                    self.console.print_console(value, CONSOLE_NORM)
                else:
                    self.console.print_error(f"Unknown key '{key}'")
            else:
                self.console.print_error("You are only allowed to enter one argument")
                return False
        except IndexError:
            self.console.print_error(f"'key' argument required")
            return False

    def handle_command_set(self, argument: list = []):
        try:
            argument_length = len(argument)
            if argument_length == 2:
                key_setting = argument[0]
                value_setting = argument[1]
                if key_setting == "port":
                    self.environment.update("port", value_setting)
                    return True
                elif key_setting == "baudrate":
                    if isDigit(value_setting):
                        self.environment.update("baudrate", int(value_setting))
                        return True
                    else:
                        self.console.print_error("You must enter numbers not letters")
                        return False
            else:
                self.console.print_error("'value' argument required")
                return False
        except IndexError:
            self.console.print_error(f"'key' argument required")
            return False

    def handle_help(self):
        username = self.environment.select("user")
        command_helper(username)
        return False

    def handle_command(self, command: str, argument: list = []):
        if command == "quit" or command == "q":
            self.console.quit(isUser=True, interrupt=False)
        elif command == "help":
            self.handle_help()
        elif command == "use":
            self.handle_command_use(argument)
        elif command == "set":
            self.handle_command_set(argument)
        elif command == "show":
            self.handle_command_show(argument)
        else:
            self.console.print_error(f"Unknown command ")