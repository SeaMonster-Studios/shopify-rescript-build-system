# ReasonReact + Shopify (Linux/macOS/Windows)

Use ReasonReact in a Shopify theme with Prepros.

## Directory structure

```
bsconfig.json
package.json
webpack.config.js
yarn.lock
src/
...ReasonML files
theme/
  -config.yml file
  ...remaining theme files
```

## Project Setup

1. Make sure you have [Shopify's themekit](https://shopify.github.io/themekit/) installed globally, `npm i -g themekit`.
2. Make sure you have [Prepros](https://prepros.io/) version 7 or later installed. 
3. Put your theme files into the `theme` directory
4. Get Shopify API Access via a priate app. Instructions can be found under the "Get API Access" setion on [this page](https://shopify.github.io/themekit/). Then copy the password to your private app.
5. Put your Shopify _store_ and private app _password_ in the `theme/config.yml` file.
6. Locate your _theme_id_:
   1. Go to the `Themes` setion of your Shopify store.
   2. Click on the `Actions` menu next to the theme you are developing and click on `Edit code`.
   3. You'll now see your theme_id (series of numbers) at the end of the URL. Copy it and paste it your theme/config.yml` file).
7. If you're not using the current published theme you'll need this extra step to get a proxy URL for Prepros that includes your theme id:
   1. Go back to `Themes` section of your Shopify store.
   2. Click on the `Actions` menu next to the theme you are developing and click on `Preview`.
   3. You'll see a tool bar displayed by Shopify fixed to the bottom of the screen. Click on the "Share preview" button.
   4. Copy the link provided to your clipboard.
8. Follow [these instructions](https://www.shopify.com/partners/blog/live-reload-shopify-sass) from Shopify to get your theme live reloading with Prepros. Some important notes:
   1. Skip step 1: You've already done most of this, and we go over `theme watch` later.
   2. Probably skip step 2: You can choose to use Prepros for processing scss or other files if you want, but it's irrelvent to this Shopify + ReasonReact starter.
   3. In step 3: Of you're not using the current pulished theme, instead of using your Shopify store URL in the "Link live preview to your store url", use the URL you got from "Share preview" in the previous step.
   4. Also in step 3: I've found a 5000 "Live Reload Delay" usually suffices for my laptop over WiFi. Of course you may need more or less of a delay depending on your computer and internet connection. Why such a long delay? Bucklescript compiles reason to JS (SUUUUPER FAST). But then webpack copies that file to the `theme/assets` directory, and then themekit processes and uploads that file to Shopify.
   5. I'd also recommending turning of any kind of compilation, uglification, etc. for your react.bundle.js file in Prepros.
9. Add the following before the closing body tag in `theme.liquid`.

```
  <div id="react-mount-main"></div>
  <div id="react-mount-app"></div>

  <script>

    if (window.location.hostname === "localhost") {

      let script = document.createElement('script'); 
      script.src = "https://localhost:5555/theme/assets/index.dev-dist.js"
      document.head.appendChild(script)
    } else {
      let script = document.createElement('script'); 
      script.src = "{{ 'index.prod-dist.js' | asset_url }}"
      document.head.appendChild(script)
    }

  </script>
```

10. Be sure to add your `<div>` with the correct id that you're mounting too (determined in `src/Index.re`).
11. Install node modules from the root directory
    > `yarn`
12. Build and watch your ReasonML files run, and watch your theme files (via themekit) simply run:
    > `yarn start`

When you're done with development to get the smallest bundle file and upload it to Shopify run:

> `yarn build`

## Mounting Points (Not an SPA)

This is not meant to be an SPA. As such it's setup for multiple mount points. In `Index.re` you will find a `mounts` type which you provide the root id of where to mount it as well as the root component/node to mount. So, when you need to setup a new mount point just add it to the `mounts` array. Each mount point will be mounted via a React Portal so that if you have shared context or state across component it will be maintained.

## Including a .scss file in a .re file

```reason
[%raw {|require('./Alert.scss')|}];
```
