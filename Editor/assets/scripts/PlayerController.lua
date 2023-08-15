local xPos = 0.0
local yPos = 0.0

local speed = 2.0

function Start()
    Transform.SetPosition(0.0, 0.0, 0.0)
end

function Update(deltaTime)
    local deltaX = 0.0
    local deltaY = 0.0

    if Input.IsKeyDown(KeyCode.D) then
        deltaX = 1.0
    elseif Input.IsKeyDown(KeyCode.A) then
        deltaX = -1.0
    end

    if Input.IsKeyDown(KeyCode.W) then
        deltaY = 1.0
    elseif Input.IsKeyDown(KeyCode.S) then
        deltaY = -1.0
    end

    deltaX = deltaX * speed * deltaTime
    deltaY = deltaY * speed * deltaTime

    Transform.Translate(deltaX, deltaY, 0.0)
end