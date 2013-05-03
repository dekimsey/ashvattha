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

commonBuild = ->
  exec 'mkdir --parents dist', loggerIgnore
  exec 'cp --recursive web/* dist', loggerIgnore
  exec 'coffee --compile lib/ src/', logger
  exec "node r.js -o build.js optimize=#{optimize}", logger

task 'build', 'Build project from src/*.coffee to lib/*.js', ->
  optimize = 'none'
  commonBuild()

task 'dist', 'Concatenate and compress', ->
  commonBuild()

task 'prepare', 'Gather project dependencies', ->
  exec 'bower install', logger
  exec 'ln -s node_modules/requirejs/bin/r.js', logger

task 'clean', 'Remove built files', ->
  exec 'rm --force --recursive dist', logger

task 'reset', 'Remove all built and prepared files', ->
  invoke 'clean'
  exec 'rm --force r.js', logger
  exec 'bower uninstall', logger
  exec 'rm --force --recursive deps', logger

