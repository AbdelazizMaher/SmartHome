const express = require('express');
const cors = require('cors');
const fs = require('fs');
const { exec } = require('child_process');

const app = express();

app.use(cors()); // Enable CORS for all routes
app.use(express.raw({ type: 'application/octet-stream', limit: '10mb' })); // Handle raw binary data

app.post("/upload", (req, res) => {
    const newPath = '/tmp/new_cppApp';

    console.log('Receiving file...');
    
    const writeStream = fs.createWriteStream(newPath);

    req.pipe(writeStream);

    writeStream.on('finish', () => {
        console.log('File received and saved to temporary path:', newPath);

        // Check if the uploaded file has a valid size
        fs.stat(newPath, (err, stats) => {
            if (err) {
                console.error('Error checking file size:', err);
                return res.status(500).send('Error checking file size.');
            }

            if (stats.size === 0) {
                console.error('Uploaded file is empty.');
                return res.status(400).send('Uploaded file is empty.');
            }

            try {
                // Remove the old binary
                if (fs.existsSync('/usr/bin/Device-Controller')) {
                    console.log('Old binary found, removing it...');
                    fs.unlinkSync('/usr/bin/Device-Controller'); // Synchronously remove old binary
                    console.log('Old binary removed.');
                } else {
                    console.log('No old binary found, skipping removal.');
                }

                // Move the new binary
                console.log('Moving new binary to /usr/bin/Device-Controller...');
                fs.renameSync(newPath, '/usr/bin/Device-Controller'); // Synchronously move new binary
                console.log('New binary moved to /usr/bin/Device-Controller.');

                // Force reboot
                console.log('Rebooting system...');
                exec('reboot -f', (err) => {
                    if (err) {
                        console.error('Error rebooting system:', err);
                        return res.status(500).send('Error rebooting system.');
                    }

                    console.log('Reboot command executed successfully.');
                    res.send('Update successful. Rebooting...');
                });
            } catch (err) {
                console.error('Error replacing binary or rebooting:', err);
                return res.status(500).send('Error replacing binary or rebooting.');
            }
        });
    });

    writeStream.on('error', (err) => {
        console.error('Error saving file:', err);
        return res.status(500).send('Error saving file.');
    });
});

app.listen(8080, () => {
    console.log('Server listening on port 8080');
});
