# ReScript + ReasonReact + Shopify

Use ReasonReact in a Shopify theme with Prepros.

## Directory structure

```
bsconfig.json
package.json
webpack.config.js
yarn.lock
src/
...ReScript files
theme/
  -config.yml file
  ...remaining theme files
```

## Initializing a new project 

### Prereqs
1. Make sure you have [Shopify's themekit](https://shopify.github.io/themekit/) installed globally, `npm i -g themekit`.
2. Make sure you have [Prepros](https://prepros.io/) version 7 or later installed. 

### Project Setup

1. In your shopify store, create two duplicates of your production theme. One will be used while actively developing the theme, while the other will be used to snapshot features/fixes that are ready for the client to preview. Identify the duplicates with a name prefix like  `Seamonster Dev ::`  and `SeaMonster Stage ::`.
2. Edit `theme/config.yml`. This contains sections that should correspond to the themes that were previously created. 
   * The `store` follows the pattern `your-store-name.myshopify.com`.
   * The `password` is a private app password that can be created using the [Themekit Access](https://apps.shopify.com/theme-kit-access?shpxid=a8e67f54-3B47-4818-715D-2431CE697661) app.
   * Locate your `theme_id`:
      1. Go to the `Themes` setion of your Shopify store.
      2. Click on the `Actions` menu next to the theme you are developing and click on `Edit code`.
      3. You'll now see your theme_id (series of numbers) at the end of the URL. Copy it and paste it your theme/config.yml` file).
3. Run `yarn prod:pull`. If everything was configured correctly this will pull the production theme files into this project's `theme` folder.
4. Get a proxy URL for Prepros that includes your theme id:
   1. Go back to `Themes` section of your Shopify store.
   2. Click on the `Actions` menu next to the theme you are developing and click on `Preview`.
   3. You'll see a tool bar displayed by Shopify fixed to the bottom of the screen. Click on the "Share preview" button.
   4. Copy the link provided to your clipboard.
5.  Follow [these instructions](https://www.shopify.com/partners/blog/live-reload-shopify-sass) from Shopify to get your theme live reloading with Prepros. Some important notes:
   1. Skip step 1: You've already done most of this, and we go over `theme watch` later.
   2. Probably skip step 2: You can choose to use Prepros for processing scss or other files if you want, but it's irrelvent to this Shopify + ReasonReact starter.
   3. In step 3: Of you're not using the current pulished theme, instead of using your Shopify store URL in the "Link live preview to your store url", use the URL you got from "Share preview" in the previous step.
   4. Also in step 3: I've found a 5000 "Live Reload Delay" usually suffices for my laptop over WiFi. Of course you may need more or less of a delay depending on your computer and internet connection. Why such a long delay? Bucklescript compiles reason to JS (SUUUUPER FAST). But then webpack copies that file to the `theme/assets` directory, and then themekit processes and uploads that file to Shopify.
   5. I'd also recommending turning of any kind of compilation, uglification, etc. for your react.bundle.js file in Prepros.
6.  Add the following immediately after the _opening_ `<body>` tag:
  ```
    <script>
      var loadStylesheet = function (url) {
        var newSS = document.createElement('link');
        newSS.rel = 'stylesheet';
        newSS.href = url;
        document.getElementsByTagName("head")[0].appendChild(newSS);
      }

      if (window.location.hostname === "localhost") {
        loadStylesheet("https://localhost:8848/theme/assets/index-dev.css")
      } else {
        loadStylesheet("{{ 'index-prod.css' | asset_url }}")
      }
    </script>

  ```
7. Add the following before the closing `</body>` tag in `theme.liquid`.

```
  <div id="react-mount-main"></div>
  <div id="react-mount-app"></div>

  <script>

    if (window.location.hostname === "localhost") {

      let script = document.createElement('script'); 
      script.src = "https://localhost:8848/theme/assets/index.dev-dist.js"
      document.head.appendChild(script)
    } else {
      let script = document.createElement('script'); 
      script.src = "{{ 'index.prod-dist.js' | asset_url }}"
      document.head.appendChild(script)
    }

  </script>
```

8. Be sure to add your `<div>` with the correct id that you're mounting too (determined in `src/Index.re`).
9.  Install node modules from the root directory
    > `yarn`
10. Build and watch your ReScript files run, and watch your theme files (via themekit) simply run:
    > `yarn dev`

When you're done with development to get the smallest bundle file and upload it to Shopify run:

> `yarn build`

And then right-click on `index.prod.js` in Prepros and click `process file` while the `watch` script is running.

### Mounting Points (Not an SPA)

This is not meant to be an SPA. As such it's setup for multiple mount points. In `Index.re` you will find a `mounts` type which you provide the root id of where to mount it as well as the root component/node to mount. So, when you need to setup a new mount point just add it to the `mounts` array. Each mount point will be mounted via a React Portal so that if you have shared context or state across component it will be maintained.


## Development Workflow

### Development
1. Clone the repo for the desired shopify site. (If one does not exist please see the [New Shopify Projects](#new-shopify-projects) section for instructions for setting up a new project.)
2. Add the directory to prepros.
   1. Open Prepros
   2. Select Add Project
   3. Find the cloned repo and add it.
3. Get a proxy URL for Prepros that includes your theme id:
   1. Go back to `Themes` section of your Shopify store.
   2. Click on the `Actions` menu next to the theme you are developing and click on `Preview`.
   3. You'll see a tool bar displayed by Shopify fixed to the bottom of the screen. Click on the "Share preview" button.
   4. Copy the link provided to your clipboard.
   5. Right click the project in Prepros. Select "Project Settings" and paste the link into "External Server URL".
4. Run `yarn prod:pull` which will automatically fetch and commit any changes to the live production theme.
5. Run `yarn` from from a terminal in your project workspace to install any node module dependencies. 
6. Run `yarn dev` to start relevant build tooling in watch mode. This includes the Rescript compiler and Shopify Themekit which immediately deploys your changes to the development store on Shopify.
7. In Prepros, right click your project and select "Open Secure Preview" to open a browser window that prepros will automatically reload whenever changes are made to project files.
8. Checkout a new branch for your feature.

### Staging a new feature
This assumes you've been working on a feature branch.
1. Run `yarn build`
2. In prepros right click `index.prod.js` and click process file. This will create a minified build of any javascript assets.
3. Commit changes.
4. Checkout the `staging` branch.
5. Run `yarn stage:pull` as a sanity check to capture any changes that may have been performed on the staging theme through the shopify editor.
6. If there are differences after the pull, checkout a new branch and create a PR to staging where you can request feedback from the team about the changes introduced. It's possible we may need to "cherry-pick" changes on a file/line level.
7. Now that the staging code and staging theme are in sync, create a PR from your actual feature branch to staging.
8. Once the feature has passed through code review and is merged in to staging, checkout the staging branch and run `yarn stage:deploy` to deploy changes to the staging store.

### Deploying to production
1. Run `yarn build`
2. In prepros right click `index.prod.js` and click process file. This will create a minified build of any javascript assets.
3. Commit changes.
4. Checkout the `main` branch (this may be called `prod` or `master` in some cases but moving forward the github default is `main`)
5. Run `yarn prod:pull` and inspect any changes that may have been introduced on the production site and commit those changes.
6. This ensures that we have a snapshot of the theme that we can restore that will be in the condition it was in pre-deployment.
7. I `yarn prod:pull` introduced new changes (and thus a new commit) you should merge `main` back into staging and perform a final sanity check on staging.
8. Once that check passes merge staging into prod and then run `yarn prod:deploy`

## Tips and Tricks

### Including a .scss file in a .re file

```reason
[%raw {|require('./Alert.scss')|}];
```