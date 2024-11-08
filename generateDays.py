import os

year = "2015"

class Template:
    name: str = None
    content: str = None

    def __init__(self, path: str):
        self.name = os.path.basename(path)
        with open(path) as file:
            self.content = file.read()

    def get_replaced(self, day_name: str) -> str:
        return (self.content
                .replace("REPLACE_DAY", day_name)
                .replace("REPLACE_YEAR", year))



templates = []
for template_name in os.listdir("templates"):
    templates.append(Template(f"templates/{template_name}"))


def create_day(day: int) -> bool:
    day_name = f"{day:02}"
    dir_path = f"./src/{day_name}"
    if os.path.isdir(dir_path) and len(os.listdir(dir_path)) != 0:
        return False


    os.makedirs(dir_path)
    for template in templates:
        with open(f"{dir_path}/{template.name}", "w") as file:
            file.write(template.get_replaced(day_name))

    return True


num_generated_days = len(list(0 for day in range(1, 26) if create_day(day)))
print(f"successfully generated {num_generated_days} days")

