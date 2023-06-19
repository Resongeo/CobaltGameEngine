local x
local y
local Ox
local Oy
local speed = -1.0
local radius = 2.0

function Start()
	x = 0
	y = 0
	Ox = Transform.GetPositionX()
	Oy = Transform.GetPositionY()

	ASDLOG()
end

function Update(deltaTime)
	Transform.SetPosition(Ox + math.cos(x) * radius, Oy + math.sin(y) * radius, 0)
	Transform.RotateZ(100 * speed * deltaTime)

	x = x + deltaTime * speed
	y = y + deltaTime * speed

	if Input.IsKeyDown(87) then speed = 3.0 else speed = 1.0 end
end