define ['toxi/math/noise/simplexNoise', 'ash/math/random'], (simplexNoise, ashRandom) ->
  ashNoise =
    # val elem [0, 1)
    normalize: (val, min, max) ->
      [min, max] = [0, 255] unless min? and max?
      avg = Math.abs((max - min) / 2)
      val * Math.floor(avg) + Math.ceil(avg)

    noise: (x, y, z, w) ->
      simplexNoise.noise(x, y, z, w)

    grid: (width, height, options) ->
      unless width? and height?
        width = options.width
        height = options.height
      random = ashRandom.rng(options.seed)
      offsetX = options.offsetX or random * ashRandom.MAX_INT
      offsetY = options.offsetY or random * ashRandom.MAX_INT
      frequencyX = options.frequencyX or options.frequency or random.range(0.005, 0.05)
      frequencyY = options.frequencyY or frequencyX

      for i in [0..width]
        for j in [0..height]
          x = i * frequencyX + offsetX
          y = j * frequencyY + offsetY
          ashNoise.normalize ashNoise.noise(x, y)
