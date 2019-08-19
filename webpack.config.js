const path = require('path');
const outputDir = path.join(__dirname, 'theme/assets/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './lib/js/src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'react.bundle.js'
  },
};
