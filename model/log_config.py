import logging
import datetime
_verbose = 1
def set_log_level(verbose):
    global _verbose
    _verbose = verbose

def get_log_level():
    return _verbose


def setlog(name="test",level=logging.INFO):
    logger = logging.getLogger()

    logger.setLevel(level)

    log_format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
    formatter = logging.Formatter(log_format)

    console_handler = logging.StreamHandler()
    console_handler.setFormatter(formatter)
    now = datetime.datetime.now()
    log_time = now.strftime("%Y-%m-%d_%H")
    file_handler = logging.FileHandler(f"{name}_{log_time}.log",mode='w')  # 输出日志到 app.log 文件
    file_handler.setFormatter(formatter)

    logger.addHandler(console_handler)
    logger.addHandler(file_handler)

