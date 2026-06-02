
import sys
import time

class ProgressBar:
    def __init__(self, total, width=50):
        self.total = total
        self.width = width
        self.current = 0

    def update(self, step=1):
        self.current += step
        percent = self.current / self.total
        filled = int(self.width * percent)
        # bar = '█' * filled + ' ' * (self.width - filled)
        # bar = '█' * filled + '>' * (self.width - filled)
        # bar = '█' * filled + '.' * (self.width - filled)
        # bar = '*' * filled + ' ' * (self.width - filled)
        # bar = '*' * filled + '-' * (self.width - filled)
        # bar = '-' * filled + ' ' * (self.width - filled)
        bar = '-' * filled + '.' * (self.width - filled)
        
        # 使用 sys.stdout.write 直接写入
        sys.stdout.write(f'\r|{bar}| {percent*100:.1f}%')
        sys.stdout.flush()
        
        if self.current >= self.total:
            sys.stdout.write('\n') # 完成后换行

    def finish(self):
        if self.current < self.total:
            self.update(self.total - self.current)

# 使用示例
if __name__ == "__main__":
    total_tasks = 100
    pb = ProgressBar(total_tasks)
    
    for _ in range(total_tasks):
        # 模拟任务处理
        time.sleep(0.01)
        pb.update()
    
    pb.finish()
