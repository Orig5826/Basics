-- lua与c相互调用参考示例
-- lua优势：
-- 1. 动态更新（也即主程序运行期间，可以随时修改lua程序，不影响主程序的运行）
--    // 当然了，lua修改保存的时候，如果有语法错误，还是会主程序异常的哦(^.^)

local n, sum = get_sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
print("num: ", n);
print("sum: ", sum);

function echo(data)
    print("data: ", data)
    return data
end

----------------------------------------------------------

function closure()
    local count = 0
    function closure_fun()
        count = count + 1
        return count
    end
    return closure_fun
end

function main()
    -- 闭包测试
    c = closure()
    print(type(c))
    for i = 1, 10, 1 do
        print(c())
    end
end

-- main()
