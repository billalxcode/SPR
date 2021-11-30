from src.python.terminal import Console
from src.python.terminal import CONSOLE_NORM
from src.python.utils import Text

console = Console()

def command_helper(username: str = ""):
    text = Text()
    text.create_new("help")
    text.append(f"Hello, {username}")
    text.append("Sistem Pendingin Ruangan (Indonesian) or Air Conditioning System is a tool to detect the room temperature and turn on the air conditioner automatically")
    text.append("In this mode you can control the tool with a command line interface, some commands are ready to use.")
    text.append("If you want to run a command, your command must start with '!', without it the command cannot be executed.")
    text.append("")
    text.append("Command: ")
    text.append("  quit         = Exit this tool")
    text.append("  use [module] = Using ready-to-use modules,")
    text.append("                 for example the 'lcd' module to monitor the lcd")
    text.append("Example: ")
    text.append("  !use lcd     = Using the lcd module to monitor the state")
    output = text.get("help")
    console.print_console(output, CONSOLE_NORM)

def command_use_helper():
    text = Text()
    text.create_new("use")
    text.append("Commands to use the module embedded in the tool")
    text.append("Example: ")
    text.append("  use lcd")