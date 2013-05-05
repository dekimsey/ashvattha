{exec} = require 'child_process'

loggerIgnore = (err, stdout, stderr) ->
  console.log stdout + stderr if stdout or stderr

logger = (err, stdout, stderr) ->
  loggerIgnore(err, stdout, stderr)
  throw err if err

optimize = 'uglify'
min = ''
jquery = 'jquery-2.0.0'
jqueryLink = "http://code.jquery.com/#{jquery}"
rjs = 'lib/r.js/dist/r.js'

commonBuild = ->
  exec 'mkdir --parents dist', loggerIgnore
  exec 'cp --recursive web/* dist', loggerIgnore
  exec 'coffee --compile lib/ src/', logger
  exec "node #{rjs} -o build.js optimize=#{optimize}", logger

task 'build', 'Build project from src/*.coffee to lib/*.js', ->
  optimize = 'none'
  commonBuild()

task 'dist', 'Concatenate and compress', ->
  commonBuild()

task 'clean', 'Remove built files', ->
  exec 'rm --force --recursive dist', logger
