inherit form [[Container]]
## name (required)
type name of the container 
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
- each image is define by x, y, w, h (% by width and height of the image that specify by "path" attribute)
- addition:
	- repeat
	- axis: choose direction (vertical or horizontal)
	- gapX
	- gapY 
	- dx
	- dy 
## sample 
```
"name": "main"
"textures":
  - 
    "path": "45908.png" 
    # "resize": [100, 200] in pixel
    "graphics":
      -
        "x": 0
        "y": 0 
        "w": 50
        "h": 50
      -
        "x": 50
        "y": 0 
        "w": 50
        "h": 50
        "gapX": 0  
        "gapY": 0
        "repeat": 1
        "axis": "vertical" 
        "dx": 1
        "dy": 1
```
