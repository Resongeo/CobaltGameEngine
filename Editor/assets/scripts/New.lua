local x = 0

function Start()
    Transform.SetPositionY(0)
end

function Update(deltaTime)
	Transform.SetPositionX(math.sin(x))
	x = x + deltaTime * 2.0
end