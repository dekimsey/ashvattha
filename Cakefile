{exec} = require 'child_process'

loggerIgnore = (err, stdout, stderr) ->
  console.log stdout + stderr if stdout or stderr

logger = (err, stdout, stderr) ->
  loggerIgnore(err, stdout, stderr)
  throw err if err

optimize = 'uglify'
min = ''
rjs = 'vendor/r.js/dist/r.js'

commonStage = ->
  exec 'mkdir stage', loggerIgnore
  exec 'mkdir stage/js', loggerIgnore
  exec 'mkdir dist', loggerIgnore
  exec 'cp --recursive web/* stage', logger
  exec 'cp --recursive vendor/* stage/js', logger
  exec 'coffee --compile stage/js src/', logger

commonBuild = ->
  exec 'cp --recursive stage/* dist', loggerIgnore

task 'build', 'Build project from src/*.coffee to vendor/*.js', ->
  optimize = 'none'
  commonStage()
  commonBuild()

task 'dist', 'Concatenate and compress', ->
  commonStage()
  jqueryBase = 'stage/js/jquery'
  exec "mv #{jqueryBase}/jquery.js #{jqueryBase}/jquery.full.js", logger
  exec "mv #{jqueryBase}/jquery.min.js #{jqueryBase}/jquery.js", logger
  exec "node #{rjs} -o build.js optimize=#{optimize}", logger
  commonBuild()

task 'clean', 'Remove built files', ->
  exec 'rm --force --recursive stage', logger
  exec 'rm --force --recursive dist', logger
