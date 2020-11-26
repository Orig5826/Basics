local usb = require("usbdisk")

function tbprint(tb,ss)
	local s = ""
	if ss ~= nil then
		s = s .. ss
	end
	
	for i=1,#tb do
		s = s .. string.format("%02x ",tb[i])
		-- print(s)
	end	
	print(s)
end

dev = usb.open("HSEC    usb2uart_c1test 0002")
cmd = {0x00,0x84,0x00,0x00,0x10}
usb.write(dev,cmd)
tbprint(cmd,"-> ")

res = usb.read(dev,18)
tbprint(res,"<- ")

usb.close(dev)
