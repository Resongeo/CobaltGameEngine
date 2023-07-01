local x = 0
local hue = 0

function Start()
    Transform.SetPositionY(0)
end

function Update(deltaTime)
	Transform.SetPositionX(math.sin(x) * 0.1)
	x = x + deltaTime * 40.0

    SpriteRenderer.SetColorHSV(hue, 0.5, 1.0)
	hue = hue + deltaTime * 100.0
	if hue >= 360 then hue = 0 end
end