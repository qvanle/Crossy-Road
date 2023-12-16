inherit form [[Container]]

## name (required)
type name of the interface
## textures (required)
### path (required)
path to the image that store in assets/graphics folder 

```
Example: the image is store in assests/graphics/background/1.jpg
>> "path": "background/1.jpg"
```

### resize (array that contain 2 element)
resize the image that specified by "path" attribute (in pixel)
### graphics (2d array of images) (required)
#### each element of graphics is a vector of images 
each image is define by x, y, w, h (% by width and height of the image that specify by "path" attribute)
- addition:
	- repeat
	- axis: choose direction (vertical or horizontal)
	- gapX
	- gapY 
	- dx
	- dy 

### buttons (vector of button)

### event 

### control 

## sample 
```
"name": "test" # require
"textures":  # require
  -
    "path": "45908.png"  # require
    "graphics":  #require
      -
        "x": 10
        "y": 10
        "w": 80
        "h": 80
        "gapX": 0  
        "gapY": 0
        "repeat": 1
        "axis": "vertical" 
        "dx": 1
        "dy": 1
"buttons": 
	-
		"name": "start" 
		"x": 40 # location of start button relatives to test interface in % 
		"y": 40 
		"w": 20
		"h": 20
	-
		"name": "pause"
		"x": 90
		"y": 90
		"w": 10
		"h": 10	
```
