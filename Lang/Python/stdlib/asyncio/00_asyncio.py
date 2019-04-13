
import asyncio
import time

# 公共函数


async def say_after(delay, what):
    await asyncio.sleep(delay)
    print(what)


def asyncio_test():
    async def main():
        print('started at', time.strftime('%X'))

        await say_after(1, 'hello')
        await say_after(2, 'world')

        print('finished at', time.strftime('%X'))

    asyncio.run(main())


def asyncio_test2():
    """
        通过运行该函数，可以明显的看出
        该示例比 asyncio_test 要快
    """
    async def main():
        task1 = asyncio.create_task(say_after(1, 'hello'))

        task2 = asyncio.create_task(say_after(2, 'world'))

        print('started at', time.strftime('%X'))

        # Wait until both tasks are completed (should take
        # around 2 seconds.)
        await task1
        await task2

        print('finished at', time.strftime('%X'))

    asyncio.run(main())


asyncio_test()
asyncio_test2()
