display.setStatusBar(display.HiddenStatusBar)
local physics = require "physics"
physics.start()
physics.setGravity(0,0)

local background = display.newImage("background.jpg")

local happy = display.newImage("happy.png")
happy.x=100
happy.y=100
physics.addBody(happy, "dynamic")

local angry = display.newImage("angry.png")

angry.x=880
angry.y=560
physics.addBody(angry, "static")

local angry2 = display.newImage("angry.png")

angry2.x=840
angry2.y=520
physics.addBody(angry2, "static")

function touchScreen(event)
	if event.phase == "began" then
		print(event.y)
		transition.to(happy,{time=1000,x=event.x, y=event.y})
	end
end

Runtime:addEventListener("touch", touchScreen)

function moveAngry()
	transition.to(angry,{time=1000,x=math.random(80,880), y=math.random(60,640)})
	transition.to(angry2,{time=1000,x=math.random(80,880), y=math.random(60,640), onComplete=moveAngry})
end

moveAngry()

function onCollision(event)
	print("collide!")
	happy:removeSelf()
end

Runtime:addEventListener("collision", onCollision)