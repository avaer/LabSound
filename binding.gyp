{
  'targets': [
    {
      'target_name': 'webaudio',
      'sources': [
        'main.cpp',
        "<!@(node -p \"require('fs').readdirSync('./lib/src').map(f=>'lib/src/'+f).join(' ')\")"
      ],
      'include_dirs': [
        "<!(node -e \"require('nan')\")",
        '<(module_root_dir)/lib/include',
        '<(module_root_dir)/labsound/include',
        '<(module_root_dir)/labsound/third_party',
        "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/include')\")"
      ],
      'conditions': [
        ['OS=="linux"', {
          'library_dirs': [
            '<(module_root_dir)/labsound/bin',
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/linux')\")",
          ],
          'libraries': [
            '-lLabSound',
            # '-ljack',
            '-lasound',
            # '-lpulse',
            # '-lpulse-simple',
            '-lavformat',
            '-lavcodec',
            '-lavutil',
            '-lswscale',
            '-lswresample',
          ],
          'ldflags': [
            '-Wl,-Bsymbolic',
          ],
        }],
      ['OS=="win"', {
        'configurations': {
          'Debug': {
            'msvs_settings': {
              'VCCLCompilerTool': {
                'RuntimeLibrary': '3' # /MDd
              },
            },
            'library_dirs': [
              '<(module_root_dir)/labsound/build/x64/Debug',
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win')\")",
            ],
          },
          'Release': {
            'library_dirs': [
              '<(module_root_dir)/labsound/build/x64/Release',
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win')\")",
            ],
          },
        },
        'copies': [{
          'destination': '<(module_root_dir)/build/Debug/',
          'files': [
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avformat-58.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avcodec-58.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avutil-56.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/swscale-5.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/swresample-3.dll')\")",
          ]
        }, {
          'destination': '<(module_root_dir)/build/Release/',
          'files': [
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avformat-58.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avcodec-58.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/avutil-56.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/swscale-5.dll')\")",
          "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/win/swresample-3.dll')\")",
          ]
        }],
        'libraries': [
          'LabSound.lib',
        'avformat.lib',
        'avcodec.lib',
        'avutil.lib',
        'swscale.lib',
        'swresample.lib',
        ],
      }],
        ['OS=="mac"', {
        'library_dirs': [
            '<(module_root_dir)/labsound/bin',
            "<!(node -e \"console.log(require.resolve('native-video-deps').slice(0, -9) + '/lib/macos')\")",
          ],
          'libraries': [
            '-framework Cocoa',
            '-framework Accelerate',
            '-framework CoreAudio',
            '-framework AudioUnit',
            '-framework AudioToolbox',
            '-llabsound',
            '-lavcodec',
            '-lavformat',
            '-lswscale',
            '-lavresample',
            '-lavutil'
          ],
          'library_dirs': [
            '<(module_root_dir)/labsound/bin',
          ],
        }],
      ],
    }
  ]
}

