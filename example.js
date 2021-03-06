const path = require('path');
const fs = require('fs');
const {AudioContext, Audio, MicrophoneMediaStream} = require('.');

// microphone
const audioContext = new AudioContext();
const mediaStream = new MicrophoneMediaStream();
const audioCtx = new AudioContext();
const microphoneSourceNode = audioCtx.createMediaStreamSource(mediaStream);

const buffers = [];

const scriptProcessorNode = audioCtx.createScriptProcessor(256, 1, 1);
scriptProcessorNode.onaudioprocess = e => {
  const float32Array = e.inputBuffer.getChannelData(0);

  const audioMessage = new Float32Array(float32Array.length);
  audioMessage.set(float32Array);
  buffers.push(audioMessage);

  // console.log('process');

  e.outputBuffer.getChannelData(0).fill(0);
};
microphoneSourceNode.connect(scriptProcessorNode);
scriptProcessorNode.connect(audioCtx.destination);

const scriptProcessorNode2 = audioCtx.createScriptProcessor(256, 1, 1);
scriptProcessorNode2.onaudioprocess = e => {
  if (buffers.length >= 2) {
    e.outputBuffer.copyToChannel(buffers.shift(), 0);
  } else {
    e.outputBuffer.getChannelData(0).fill(0);
  }
};
const microphoneSourceNode2 = audioCtx.createMediaStreamSource(mediaStream);
microphoneSourceNode2.connect(scriptProcessorNode2);
scriptProcessorNode2.connect(audioCtx.destination);

setTimeout(() => {}, 100000000);

/* const path = require('path');
const fs = require('fs');
const {AudioContext, Audio, MicrophoneMediaStream} = require('.');

// microphone
const audioContext = new AudioContext();
const microphoneMediaStream = new MicrophoneMediaStream();
const audioCtx = new AudioContext();
const microphoneSourceNode = audioCtx.createMediaStreamSource(microphoneMediaStream);

const scriptProcessorNode = audioCtx.createScriptProcessor();
scriptProcessorNode.onaudioprocess = e => {
  // console.log('got event', e.inputBuffer.getChannelData(0).slice(0, 4));
  // console.log('create buffer arguments 1', e.inputBuffer.getChannelData(0).slice(0, 4));
  const buffer = audioCtx.createBuffer(e.inputBuffer.numberOfChannels, e.inputBuffer.length, e.inputBuffer.sampleRate);
  buffer.copyToChannel(e.inputBuffer.getChannelData(0), 0);
  buffers.push(buffer);
  _flushBuffer();
  e.outputBuffer.getChannelData(0).fill(0);
  // e.outputBuffer.copyToChannel(e.inputBuffer.getChannelData(0), 0);
};
microphoneSourceNode.connect(scriptProcessorNode);
scriptProcessorNode.connect(audioCtx.destination);

const bufferSourceNode = audioCtx.createBufferSource();
bufferSourceNode.connect(audioCtx.destination);
const buffers = [];
let playing = false;
const _flushBuffer = () => {
  if (!playing && buffers.length > 0) {
    bufferSourceNode.buffer = buffers.shift();
    bufferSourceNode.start();
    bufferSourceNode.onended = () => {
      bufferSourceNode.onended = null;
      playing = false;

      _flushBuffer();
    };
    playing = true;
  }
};

setTimeout(() => {}, 100000000); */

/* // audio clip
fs.readFile(path.join(__dirname, 'labsound', 'assets', 'samples', 'stereo-music-clip.wav'), (err, data) => {
  if (!err) {
    console.log('create');

    class HTMLAudioElement {
      constructor(audio) {
        this.audio = audio;
      }

      play() {
        this.audio.play();
      }

      pause() {
        this.audio.pause();
      }

      get data() {
        return this.audio.data;
      }
      set data(data) {}
    }
    const audioElement = new HTMLAudioElement(new Audio());

    console.log('load');

    audioElement.audio.load(data, 'wav');

    const audioSourceNode = audioContext.createMediaElementSource(audioElement);
    const gainNode = audioContext.createGain();
    gainNode.connect(audioContext.destination);
    const pannerNode = audioContext.createPanner();
    pannerNode.connect(gainNode);
    audioSourceNode.connect(pannerNode);

    console.log('play');

    audioElement.play();

    console.log('set timeout');

    setTimeout(() => {
      audioElement.pause();

      setTimeout(() => {}, 1000);
    }, 2000);
  } else {
    throw err;
  }
}); */
