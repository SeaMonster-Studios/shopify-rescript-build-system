const cssnano = require("cssnano")

console.log(`
  ENVIRONMENT: ${process.env.NODE_ENV}
`)

module.exports = {
  plugins: {
    tailwindcss: {},
    autoprefixer: {},
    cssnano: cssnano({
      preset: "default"
    })
  }
}