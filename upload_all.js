var serialport = require('serialport');
var spawn = require('child_process').spawn;
var fs = require('fs');

var hardware = JSON.parse(fs.readFileSync("hardware.json", "UTF-8"));
if (!('name' in hardware)) {
  throw "hardware.json must have name property -- maybe you haven't pulled?";
}

serialport.list(function(err, ports) {
  var serToCom = {};
  ports.forEach(function(p) {
    var parts;
    if (p.serialNumber) {
      parts = p.serialNumber.split('_');
      serToCom[parts[parts.length-1]] = p.comName;
    } else if (p.pnpId) {
      parts = p.pnpId.split('\\');
      if (parts.length > 1) {
        serToCom[parts[parts.length-1]] = p.comName;
      }
    }
  });

  for (var amib in hardware.AMIBs) {
    var ser = hardware.AMIBs[amib].serialNumber;
    if (!(ser in serToCom)) {
      console.log("WARNING: not uploading to " + amib + " because it doesn't appear to be connected");
      continue;
    }

    (function (amib, com) {
      var stdout = "";
      var stderr = "";
      var sketch = hardware.name + amib + "/" + hardware.name + amib + ".ino";
      var proc = spawn('arduino', ['--upload', '--board', 'arduino:avr:mega', '--port', com, sketch]);

      proc.stdout.on('data', function(data) {
        stdout += data;
      });
      proc.stderr.on('data', function(data) {
        stderr += data;
      });
      proc.on('close', function(code) {
        if (code != 0) {
          console.log("ERROR: " + amib + " failed to upload.");
          console.log(stdout);
          console.log(stderr);
        } else {
          console.log("Successfully uploaded to " + amib);
        }
      });
    })(amib, serToCom[ser]);
  }
});
