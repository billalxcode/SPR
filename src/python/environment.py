import json
import xmljson
import os
import time
import threading
from src.python.terminal import Console
from lxml.etree import fromstring, tostring

class Environment:
    def __init__(self) -> None:
        self.filename = os.path.join(os.getcwd(), ".config.json")
        self.console = Console()
        self.environments = {}
        self.thread = None
        self.thread2 = None
        self.isSave = True
        self.isLoad = True

    def kill_all(self):
        self.console.print_warning("Kill all threading...")
        self.isSave = False
        self.isLoad = False
        self.thread.join()
        self.thread2.join()

    def convert_xml2json(self, content):
        xml = fromstring(content)
        return xmljson.badgerfish.data(xml)

    def convert_json2xml(self, content, line_padding=""):
        result_list = list()
        json_obj_type = type(content)
        if json_obj_type is list:
            for sub_element in content:
                result_list.append(self.convert_json2xml(sub_element, line_padding))
            return "\n".join(result_list)

        if json_obj_type is dict:
            for tag_name in content:
                sub_obj = content[tag_name]
                result_list.append(f"{line_padding}<{tag_name}>")
                result_list.append(self.convert_json2xml(sub_obj, "\t" + line_padding))
                result_list.append(f"{line_padding}<{tag_name}>")
            return "\n".join(result_list)
        return f"{line_padding}{content}"

    def _load_from_files(self, filename: str = "", ext: str = "json"):
        while self.isLoad:
            if filename == "":
                filename = self.filename
            
            try:
                with open(filename, "r") as File:
                    content = File.read()
                    if ext == "json":
                        self.environments = json.loads(content)
                    elif ext == "xml":
                        self.environments = self.convert_xml2json(content)
            except (FileNotFoundError, IOError):
                self.console.print_error("Failed to load virtual environment, file not found", end="\n")
                self.console.quit()
            except PermissionError:
                self.console.print_error(f"Failed to load file, change permission code to 777")
                os.chmod(self.filename, 777)
            except json.decoder.JSONDecodeError: continue
            time.sleep(2)

    def _save_to_files(self, filename: str = "", ext: str = "json"):
        while self.isSave:
            if filename == "":
                filename = self.filename
            try:
                with open(filename, "w") as File:
                    content = ""
                    if ext == "json":
                        content = json.dumps(self.environments)
                    elif ext == "xml":
                        content = self.convert_json2xml(self.environments)
                    File.write(content)
                    File.close()
            except PermissionError:
                self.console.print_error(f"Failed to save file, change permission code to 777")
                os.chmod(self.filename, 777)
            
            time.sleep(2)

    def load_from_files(self, filename: str = "", ext: str = "json"):
        self.console.print_info("Load virtual environment")
        self.thread = threading.Thread(target=self._load_from_files, args=(filename, ext, ))
        self.thread.setDaemon(True)
        self.thread.start()

    def save(self, filename: str = "", ext: str = "json"):
        self.console.print_info("Save virtual environment")
        self.console.print_info(self.filename)
        self.thread2 = threading.Thread(target=self._save_to_files, args=(filename, ext, ))
        self.thread2.setDaemon(True)
        self.thread2.start()

    def create(self, key: str, value: str, force: bool = False):
        if self.environments[key] and force is True:
            self.environments[key] = value
            return True
        elif self.environments[key] and force is not True:
            return False
        else:
            self.environments[key] = value
        
    def select(self, key: str):
        try:
            return self.environments[key]
        except KeyError:
            return False

    def delete(self, key: str):
        del self.environments[key]

    def update(self, key: str, value: str):
        self.environments[key] = value

    def exists(self, key: str):
        return (True if key in self.environment else False)