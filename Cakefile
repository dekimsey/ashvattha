{exec} = require 'child_process'

nolog = ->

loggerIgnore = (err, stdout, stderr) ->
  console.log stdout + stderr if stdout or stderr

logger = (err, stdout, stderr) ->
  loggerIgnore(err, stdout, stderr)
  throw err if err

optimize = 'uglify'
min = ''
rjs = 'vendor/r.js/dist/r.js'

commonBuild = ->
  exec 'mkdir dist', nolog
  exec 'mkdir dist/js', nolog
  exec 'cp --recursive web/* dist', logger
  exec 'cp --recursive vendor/* dist/js', logger
  exec 'coffee --compile --output dist/js src', logger

task 'build', 'Build development project', ->
  optimize = 'none'
  commonBuild()

task 'dist', 'Concatenate and compress', ->
  commonBuild()
  jqueryBase = 'dist/js/jquery'
  exec "mv #{jqueryBase}/jquery.js #{jqueryBase}/jquery.full.js", logger
  exec "mv #{jqueryBase}/jquery.min.js #{jqueryBase}/jquery.js", logger
  exec "node #{rjs} -o build.js optimize=#{optimize}", logger

task 'clean', 'Remove built files', ->
  exec 'rm --force --recursive stage', logger
  exec 'rm --force --recursive dist', logger

task 'server', 'Run the test server', ->
  exec 'http-server dist', logger
