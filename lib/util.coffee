
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

module.exports = util

