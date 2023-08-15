function Start()
    Debug.Log("ASD")
end

function Update()
    if Input.IsKeyDown(KeyCode.W) then
        Debug.Warn("W is pressed!")
    end
    
    if Input.IsKeyDown(KeyCode.A6) then
        Debug.Warn("Alpha 6 is pressed!")
    end
    
    if Input.IsKeyDown(KeyCode.SPACE) then
        Debug.Warn("Space is pressed!")
    end
end