
Character =
{
	Name = "ninja",
	Position = ogre.Vector3(0,5,0),
	Size = ogre.Vector3(3.0, 10.0, 2.0),
	Yaw = -90,
	Scale = 0.05,
	
	OnCreate = 
		function( ch )
			--ch:attachEntityToBone("Sword", "Handle.L")
			--ch:attachEntityToBone("Sword", "Handle.R")
			
			-- Other anims: Backflip Climb Crouch Jump JumpNoHeight Kick SideKick Spin Stealth
			-- Walk Death1 Death2 HighJump
			
			ch:createAnimation(fts.Character_ATTACK, "Attack3")
			ch:createAnimation(fts.Character_DEFEND, "Block");
			ch:createAnimation(fts.Character_FALL, "JumpNoHeight", true);
			ch:createAnimation(fts.Character_IDLE, "Idle1", true);
			--ch:createAnimation(fts.Character_IDLE, "Idle3", true);
			ch:createAnimation(fts.Character_JUMP, "JumpNoHeight");
			ch:createAnimation(fts.Character_LAND, "Crouch");
			ch:createAnimation(fts.Character_MOVE, "Walk", true);
			--ch:createAnimation(fts.Character_MOVE, "RunBase", true);
		end,
}
	