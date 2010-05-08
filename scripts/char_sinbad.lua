
Character =
{
	Name = "sinbad",
	Position = Ogre.Vector3(0,5,0),
	Size = Ogre.Vector3(3.0, 10.0, 2.0),
	
	OnCreate = 
		function( ch )
			ch:attachEntityToBone("Sword", "Handle.L")
			ch:attachEntityToBone("Sword", "Handle.R")
		end
}
	