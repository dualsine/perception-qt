const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const HtmlWebpackInlineSourcePlugin = require('html-webpack-inline-source-plugin');
const WebpackShellPlugin = require('webpack-shell-plugin');

module.exports = {
	mode: "development",
	entry: './options_src/index.js',
	output: {
		path: path.resolve(__dirname, "dist", "options"),
		filename: 'bundle.js'
	},
	module: {
		rules: [
			{
				test: /\.js?$/,
					exclude: /(node_modules|bower_components)/,
					use: {
					loader: 'babel-loader',
					options: {
						presets: ['@babel/preset-env']
					}
				}
			},
			{
	            test: /\.scss$/,
	            use: [
					{
						loader: "style-loader" // creates style nodes from JS strings
					},
					{
						loader: "css-loader" // translates CSS into CommonJS
					},
					{
						loader: "sass-loader" // compiles Sass to CSS
					}
		        ]
	        }
		]
	},
	plugins: [
		new HtmlWebpackPlugin({
		    filename: 'index.html',
		    template: 'options_src/index.html',
	  		inlineSource: '.(js|css)$'
	    }),
  		new HtmlWebpackInlineSourcePlugin(),
  		new WebpackShellPlugin({
  			onBuildStart:[
  				'mkdir -p ./dist/options',
  				'cp -rpf ./options_src/imgs ./dist/options/.'],
  			onBuildEnd:['rm ./dist/options/bundle.js']
  		})
	]
}