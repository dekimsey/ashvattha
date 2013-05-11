define [], ->
  ashRandom =
    MAX_INT: Math.pow(2, 31) - 1
    MIN_INT: -Math.pow(2, 31)
    rng: (seed) ->
      seed = seed or new Date.getTime()
      random = ->
        seed = (seed * 9301) % 233280
        seed / 233280

      random.range = (min, max) ->
        [min, max] = [max, min] if max < min
        random() * (max - min) + min

      random
