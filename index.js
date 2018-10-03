const path = require('path');
const configuration = process.env.LABSOUND_DEBUG ? 'Debug' : 'Release';
const bindings = require(`./build/${configuration}/webaudio.node`)

const {PannerNode} = bindings;
PannerNode.setPath(path.join(__dirname, 'labsound', 'assets', 'hrtf'));

module.exports = bindings;
