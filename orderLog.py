class LogEntry(object):

    def __init__(self, sec, milisec, desc):
        self.sec = sec
        self.milisec = milisec
        self.desc = desc

    def __str__(self):
        return "(" + self.sec + " - " + self.milisec + ")" + " " + self.desc

    def __repr__(self):
        return "(" + self.sec + " - " + self.milisec + ")" + " " + self.desc


def order():

    arch = open("build/restorrente.log")
    new_log = []
    i = 0
    for line in arch:
        if (i < 4):
            i += 1
            continue
        log_data, log_desc = line.split("}")
        level, sec, sep, milisec = log_data.split()
        entry = LogEntry(sec, milisec, log_desc)
        new_log.append(entry)
    new_log.sort(key=lambda x: x.sec + x.milisec)
    print new_log
    arch.close()


order()
