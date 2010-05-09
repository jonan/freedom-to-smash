
Character =
{
	Name = "sinbad",
	Position = ogre.Vector3(0,5,0),
	Size = ogre.Vector3(3.0, 10.0, 2.0),
	Yaw = 90,
	
	OnCreate = 
		function( ch )
			ch:attachEntityToBone("Sword", "Handle.L")
			ch:attachEntityToBone("Sword", "Handle.R")
		end
}
	