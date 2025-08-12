/**
 * WEB222 – Assignment 1
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been copied
 * manually or electronically from any other source (including web sites)
 * or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name: <YOUR_NAME>
 *      Student ID: <YOUR_STUDENT_ID>
 *      Date: <SUBMISSION_DATE>
 *
 * Please see all unit tests in the files problem-00.test.js, problem-01.test.js, etc.
 */

/*******************************************************************************
 * Problem 0: learn how to implement code to pass unit tests.
 *
 * Welcome to Assignment 1! In this assignment, you're going to be practicing
 * new JavaScript programming techniques.  Before you dive in let's spend a
 * minute helping you learn how to read this code, and how to understand the
 * tests that go with it.
 *
 * In addition to this file, please also open the src/problem-00.test.js file.
 * Start by reading the comment at the top of that file, then come back here and
 * continue.
 *
 * Make sure you have completed the necessary Setup (install node.js, run `npm install`
 * before continuing).  The rest of the instructions assume that you have done this.
 *
 * After you finish reading src/problem-00.test.js, it's time to try running
 * the tests.  To run the tests, go to your terminal and type the following command:
 *
 *   npm test
 *
 * You have to run this command in the root of your project (i.e., in the same
 * directory as package.json).  When you do, you will see a lot of failures.
 * That's expected, since we haven't written any solution code yet.
 *
 * You can also run tests for only this problem instead of everything. To do that:
 *
 *   npm test problem-00
 *
 * This will look for tests that are part of the problem-00.test.js file, and only
 * run those.  Doing so should result in 1 failed and 1 passed test.
 *
 * The first test passes:
 *
 *  ✓ greeting should be a function
 *
 * But the second one fails:
 *
 * FAIL  src/problem-00.test.js > Problem 0 - greeting() function > greeting should
 * return the correct string output
 * AssertionError: expected 'Hello WEB222 Student' to be 'Hello WEB222 Student!' // Object.is equality
 *
 * Expected: "Hello WEB222 Student!"
 * Received: "Hello WEB222 Student"
 *
 * ❯ src/problem-00.test.js:70:20
 *     68|   test('greeting should return the correct string output', function ()…
 *     69|     let result = greeting('WEB222 Student');
 *     70|     expect(result).toBe('Hello WEB222 Student!');
 *       |                    ^
 *     71|   });
 *     72|
 *
 * We can see that the second test 'greeting should return the correct string output'
 * is failing. In particular, it's failing because it expected to get the string
 * "Hello WEB222 Student!" but instead it actually received the string "Hello WEB222 Student".
 *
 * It looks like we have a small typo in our code below, and we are missing
 * the final "!"" character.  Try adding it below, save this file, and re-run the
 * tests again:
 *
 * npm test problem-00
 * ✓ src/problem-00.test.js (2)
 *  ✓ Problem 0 - greeting() function (2)
 *    ✓ greeting should be a function
 *    ✓ greeting should return the correct string output *
 *
 * Excellent! At this point you're ready to move on to Problem 1. As you do,
 * read both the information in the Problem's comment, and also read the tests
 * to understand what they expect from your code's implementation.
 *
 * One final word about these comments.  You'll see comments like this one:
 *
 * @param {string} name - the name to greet in the message
 * @returns {string}
 *
 * These are specially formatted comments that define parameters to functions,
 * and tell us the type (e.g., {string} or {number}), and also the parameter's name.
 * We also indicate the return type for functions.
 *
 * Finally, we also explain a bit about how the parameter is used, and what
 * data it will have, whether it's optional, etc.
 ******************************************************************************/

function greeting(name) {
  return `Hello ${name}!`;
}

/*******************************************************************************
 * Problem 1: check if an HTTP status code is successful
 *
 * HTTP responses include a status code: an integer number between 100 and 599,
 * indicating the result of a request.  A successful response is in the range
 * 200 to 299, see https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#successful_responses
 *
 * Write a function named isSuccess() that accepts a status code argument
 * and checks if it is a successful response.
 *
 * isSuccess(100) returns false
 * isSuccess(201) returns true
 *
 * @param {number} statusCode - a status code number to be checked
 * @return {boolean} - true if the status code is successful, false otherwise
 ******************************************************************************/

function isSuccess(statusCode) {
  return statusCode >= 200 && statusCode <= 299;
}

/*******************************************************************************
 * Problem 2: add sales tax to an amount before taxes, based on the given
 * province or territory.
 *
 * In Canada, sales tax is calculated differently in region, see:
 * https://www.canada.ca/en/revenue-agency/services/tax/businesses/topics/gst-hst-businesses/charge-collect-which-rate/calculator.html
 *
 * The following chart gives the amount of sales tax for each province:
 *
 * Province/Territory        | Code | Amount
 * --------------------------|------|-------
 * Alberta                   | AB   | 5%
 * British Columbia          | BC   | 12%
 * Manitoba                  | MB   | 12%
 * New Brunswick             | NB   | 15%
 * Newfoundland and Labrador | NL   | 15%
 * Northwest Territories     | NT   | 5%
 * Nova Scotia               | NS   | 15%
 * Nunavut                   | NU   | 5%
 * Ontario                   | ON   | 13%
 * Prince Edward Island      | PE   | 15%
 * Quebec                    | QC   | 15%
 * Saskatchewan              | SK   | 11%
 * Yukon                     | YT   | 5%
 *
 * Write a function named withTax() which accepts both an amount (number) and
 * a 2-character provincial code (string), and returns the amount with the
 * proper tax added.
 *
 * For example:
 *
 * withTax(1.00, "ON") would return 1.13
 *
 * @param {number} amount - the before-tax amount
 * @param {string} code - the 2-character code for the province/territory
 * @returns {number} - the total amount with tax added
 ******************************************************************************/

function withTax(amount, code) {
  const taxRates = {
    AB: 0.05,
    BC: 0.12,
    MB: 0.12,
    NB: 0.15,
    NL: 0.15,
    NT: 0.05,
    NS: 0.15,
    NU: 0.05,
    ON: 0.13,
    PE: 0.15,
    QC: 0.15,
    SK: 0.11,
    YT: 0.05
  };

  const taxRate = taxRates[code];
  return amount * (1 + taxRate);
}

/*******************************************************************************
 * Problem 3: repeat a string
 *
 * You are asked to create a function named long(), which returns the word 'long'
 * but with the ability to specify the number of 'o's.
 *
 * For example:
 *
 * long() or long(1) return 'long'
 * long(2) returns 'loong` with 2 'o's
 * long(5) returns 'looooong' with 5 'o's
 *
 * @param {number} count - the number of 'o's to include. Defaults to 1.
 * @returns {string} - the word 'long' with the specified number of 'o's
 ******************************************************************************/

function long(count) {
  if (count === undefined || count <= 1) {
    return 'long';
  }

  let result = 'l';
  for (let i = 0; i < count; i++) {
    result += 'o';
  }
  result += 'ng';
  return result;
}

/*******************************************************************************
 * Problem 4: calculate the average for a list of numbers or numbers-as-strings.
 *
 * Write a function averageForValues() which takes any number of values and
 * returns their average.
 *
 * The list of values could include both numbers (e.g., 9 or 9.4) and strings
 * (e.g., "9" or "9.4").  Your function should be able to handle both.
 *
 * If no value is passed to the function, return zero (i.e., 0).
 *
 * @param {number | string} values - a list of one or more numbers or strings
 * @returns {string} - the formatted date string
 ******************************************************************************/

function averageForValues(...values) {
  if (values.length === 0) {
    return 0;
  }

  let sum = 0;
  for (let i = 0; i < values.length; i++) {
    sum += Number(values[i]);
  }

  return sum / values.length;
}

/*******************************************************************************
 * Problem 5: determine the MIME type from a filename
 *
 * To identify the type of a file, the Operating System looks at the filename and
 * extension. The OS needs to know the file type to open it with the correct
 * program.
 *
 * Write a function, mimeTypeFromFilename(), which should take a filename and
 * return the MIME type of the file (e.g., 'text/plain', 'image/jpeg', 'video/mp4'),
 * based on the following extensions:
 *
 * - .txt --> 'text/plain'
 * - .html, .htm --> 'text/html'
 * - .css --> 'text/css'
 * - .js --> 'application/javascript'
 * - .jpg, .jpeg --> 'image/jpeg'
 * - .png --> 'image/png'
 * - .gif --> 'image/gif'
 * - .bmp --> 'image/bmp'
 * - .svg --> 'image/svg+xml'
 * - .json --> 'application/json'
 * - .xml --> 'application/xml'
 * - .csv --> 'text/csv'
 * - .mp3 --> 'audio/mpeg'
 * - .mp4 --> 'video/mp4'
 *
 * NOTE: any other extension should return 'application/octet-stream', to indicate
 * that it is an unknown file type. You should also use 'application/octet-stream'
 * if the file has no extension.
 *
 * NOTE: The function should be case-insensitive, meaning it should treat
 * '.TXT' and '.txt' as the same extension.
 *
 * @param {string} filename - a filename, optionally with an extension
 * @returns {string}
 ******************************************************************************/

function mimeTypeFromFilename(filename) {
  const mimeTypes = {
    txt: 'text/plain',
    html: 'text/html',
    htm: 'text/html',
    css: 'text/css',
    js: 'application/javascript',
    jpg: 'image/jpeg',
    jpeg: 'image/jpeg',
    png: 'image/png',
    gif: 'image/gif',
    bmp: 'image/bmp',
    svg: 'image/svg+xml',
    json: 'application/json',
    xml: 'application/xml',
    csv: 'text/csv',
    mp3: 'audio/mpeg',
    mp4: 'video/mp4'
  };

  const lastDot = filename.lastIndexOf('.');
  if (lastDot === -1) {
    return 'application/octet-stream';
  }

  const extension = filename.slice(lastDot + 1).toLowerCase();

  return mimeTypes[extension] || 'application/octet-stream';
}

// Our unit test files need to access the functions we defined above, so we export them here.
export { greeting, isSuccess, withTax, long, averageForValues, mimeTypeFromFilename };
