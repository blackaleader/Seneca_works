import { describe, test, expect } from 'vitest';
import { mimeTypeFromFilename } from './solutions';

describe('Problem 5 - mimeTypeFromFilename() function', function () {
  test('should return text/plain for .txt files', () => {
    expect(mimeTypeFromFilename('document.txt')).toBe('text/plain');
    expect(mimeTypeFromFilename('DOCUMENT.TXT')).toBe('text/plain');
  });

  test('should return text/html for .html and .htm files', () => {
    expect(mimeTypeFromFilename('index.html')).toBe('text/html');
    expect(mimeTypeFromFilename('index.htm')).toBe('text/html');
    expect(mimeTypeFromFilename('INDEX.HTML')).toBe('text/html');
    expect(mimeTypeFromFilename('INDEX.HTM')).toBe('text/html');
  });

  test('should return text/css for .css files', () => {
    expect(mimeTypeFromFilename('styles.css')).toBe('text/css');
    expect(mimeTypeFromFilename('STYLES.CSS')).toBe('text/css');
  });

  test('should return application/javascript for .js files', () => {
    expect(mimeTypeFromFilename('app.js')).toBe('application/javascript');
    expect(mimeTypeFromFilename('APP.JS')).toBe('application/javascript');
  });

  test('should return image/jpeg for .jpg and .jpeg files', () => {
    expect(mimeTypeFromFilename('image.jpg')).toBe('image/jpeg');
    expect(mimeTypeFromFilename('image.jpeg')).toBe('image/jpeg');
    expect(mimeTypeFromFilename('IMAGE.JPG')).toBe('image/jpeg');
    expect(mimeTypeFromFilename('IMAGE.JPEG')).toBe('image/jpeg');
  });

  test('should return image/png for .png files', () => {
    expect(mimeTypeFromFilename('image.png')).toBe('image/png');
    expect(mimeTypeFromFilename('IMAGE.PNG')).toBe('image/png');
  });

  test('should return image/gif for .gif files', () => {
    expect(mimeTypeFromFilename('image.gif')).toBe('image/gif');
    expect(mimeTypeFromFilename('IMAGE.GIF')).toBe('image/gif');
  });

  test('should return image/bmp for .bmp files', () => {
    expect(mimeTypeFromFilename('image.bmp')).toBe('image/bmp');
    expect(mimeTypeFromFilename('IMAGE.BMP')).toBe('image/bmp');
  });

  test('should return image/svg+xml for .svg files', () => {
    expect(mimeTypeFromFilename('vector.svg')).toBe('image/svg+xml');
    expect(mimeTypeFromFilename('VECTOR.SVG')).toBe('image/svg+xml');
  });

  test('should return application/json for .json files', () => {
    expect(mimeTypeFromFilename('data.json')).toBe('application/json');
    expect(mimeTypeFromFilename('DATA.JSON')).toBe('application/json');
  });

  test('should return application/xml for .xml files', () => {
    expect(mimeTypeFromFilename('data.xml')).toBe('application/xml');
    expect(mimeTypeFromFilename('DATA.XML')).toBe('application/xml');
  });

  test('should return text/csv for .csv files', () => {
    expect(mimeTypeFromFilename('data.csv')).toBe('text/csv');
    expect(mimeTypeFromFilename('DATA.CSV')).toBe('text/csv');
  });

  test('should return audio/mpeg for .mp3 files', () => {
    expect(mimeTypeFromFilename('audio.mp3')).toBe('audio/mpeg');
    expect(mimeTypeFromFilename('AUDIO.MP3')).toBe('audio/mpeg');
  });

  test('should return video/mp4 for .mp4 files', () => {
    expect(mimeTypeFromFilename('video.mp4')).toBe('video/mp4');
    expect(mimeTypeFromFilename('VIDEO.MP4')).toBe('video/mp4');
  });

  test('should return application/octet-stream for unknown extensions', () => {
    expect(mimeTypeFromFilename('file.unknown')).toBe('application/octet-stream');
    expect(mimeTypeFromFilename('FILE.UNKNOWN')).toBe('application/octet-stream');
  });

  test('should return application/octet-stream for files with no extension', () => {
    expect(mimeTypeFromFilename('file')).toBe('application/octet-stream');
    expect(mimeTypeFromFilename('FILE')).toBe('application/octet-stream');
  });
});
