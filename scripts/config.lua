
Config =
{
    MsgEnabled = true,
    WelcomeMessage = "Welcome!",
    MajorVersion = 0,
    MinorVersion = 2,
    Num = 3.14,
	Player1 = "sinbad",
	Player2 = "sinbad"
}


print "[DLua] Config"




function PrintMethods(obj)
	print("****************************")
	print("Print: ", obj)
	print("SwigType: ", swig_type(obj))
	print("METHODS:")
	local meta = getmetatable(obj)
	print(meta)
	if meta == nil then
		print("No methods.")
		print("****************************")
		return
	end
	local funtable = meta['.fn']
	--table.foreach(funtable, print)
	for i, v in pairs(funtable) do print(i, v) end
	print("****************************")
end
