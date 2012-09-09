fs = require 'fs'

util =
	d: -> console.log '[debug]', arguments...
	l: -> console.log arguments...
	err: -> console.log '[error]', arguments...
	time: (descr, fn) ->
		start = new Date().getTime()
		console.log '[timer] Starting task:', descr
		result = fn()
		end = new Date().getTime()
		console.log '[timer] Finished task:', descr, "(That took #{end-start} ms.)"
		result

	# Return file or undefined if something went wrong.
	# Reports its own errors.
	getFile: (filename) ->
		try
			fs.readFileSync(filename, 'utf8')
		catch e
			if e.code == 'ENOENT'
				return util.err "File not found: #{filename}"
			else
				return util.err e.toString()
		

module.exports = util

