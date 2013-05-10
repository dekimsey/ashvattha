#this file exists to join all examples together for build purposes
requirejs.config
  baseUrl: 'js'
  paths:
    toxi: 'toxiclibsjs/lib/toxi'
  shim:
    three:
      exports: 'THREE'

define ['toxi/color'], (color) ->
  console.log color.TColor.BLACK_POINT
