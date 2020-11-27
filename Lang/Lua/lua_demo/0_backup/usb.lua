--[[
	相关接口：
	handle = usbdisk.open(symbolic_link)
	bool = usbdisk.close(handle)
	wrote_cnt = usbdisk.write(handle,table)
	table = usbdisk.read(handle,size)
]]--
local usb = require("lusbdisk")

function tbprint(tb,ss)
	local s = ""
	if ss ~= nil then
		s = s .. ss
	end
	
	for i=1,#tb do
		s = s .. string.format("%02x ",tb[i])
	end	
	print(s)
end


function usb_run(symbolic_link)
	hdev = usb.open(symbolic_link)
	if hdev == 0 then
		print("open [" .. symbolic_link .."] device failed!")
		os.exit(-1)
	end
	cmd = {0x00,0x84,0x00,0x00,0x10}
	
	cnt = 1
	for i=1,cnt do
		usb.write(hdev,cmd)
		tbprint(cmd,"-> ")
		res = usb.read(hdev,18)
		tbprint(res,"<- ")
	end
	
	usb.close(hdev)
end

usb_run("HSEC    usb2uart_c1test 0002")
