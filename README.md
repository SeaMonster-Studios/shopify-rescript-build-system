# ReasonReact with Shopify and Motifmate

Use ReasonReact in a Shopify theme with Motifmate.

- , connect that directory to Shopify with Motifmate (handles file uploads and live reload)

## Directory structure

...ReasonML files
theme/...theme files

## Project Setup

1. Drop your theme files into the `theme` directory
2. With Motifmate connect to your shopify store and then "connect" the `theme` directory to your store with Motifmate. To do connect Motifmate to the `theme` folder after connecting Motifmate to your store:
   a. Open Motifmate and select your store
   b. Click the "..." menu icon in the bottom left of the window.
   c. Hover over the "folder" option and click "connect"
   d. Select the `theme` directory of the project, _NOT_ the root of the project
3. Install node modules from the root directory
   > `yarn`
4. To build and watch your ReasonML files run:
   > `yarn start`

When you're done with development to get the smallest bundle file run:

> `yarn build`

## Mounting Points (Not an SPA)

This is not meant to be an SPA. As such it's setup for multiple mount points. In `Index.re` you will find a `mounts` type which you provide the root id of where to mount it as well as the root component/node to mount. So, when you need to setup a new mount point just add it to the `mounts` array.

## Common Problems

- Your getting a crazy amount of uplaod errors from Motfimate
  > You likely have Motifmate connected to the project root instead of the `theme` directory. Motifmate will provide an error for everyfile that's not considered a Shopify-valid theme file.
