
Character =
{
    Name = "sinbad",
    Position = ogre.Vector3(0,5,0),
    Mass = 20,
    JumpForce = 1200,
    WalkSpeed = 25,
    Size = ogre.Vector3(3.0, 10.0, 2.0),
    Yaw = 90,

    OnCreate =
        function( ch )
            ch:attachEntityToBone("Sword", "Handle.L")
            ch:attachEntityToBone("Sword", "Handle.R")

            ch:createAnimation(fts.Character_ATTACK, "SliceVertical")
            ch:createAnimation(fts.Character_DEFEND, "DrawSwords");
            ch:createAnimation(fts.Character_FALL, "JumpLoop", true);
            ch:createAnimation(fts.Character_IDLE, "IdleTop", true);
            ch:createAnimation(fts.Character_IDLE, "IdleBase", true);
            ch:createAnimation(fts.Character_JUMP, "JumpStart");
            ch:createAnimation(fts.Character_LAND, "JumpEnd");
            ch:createAnimation(fts.Character_MOVE, "RunTop", true);
            ch:createAnimation(fts.Character_MOVE, "RunBase", true);
        end,
}
