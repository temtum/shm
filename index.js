'use strict';

const { Shm } = require('bindings')('shm');

class SharedMemory {
    constructor(opts) {
        this.name = opts.name;
        this.blocks = opts.blocks;
        this.blockSize = opts.blockSize;
        this.db = new Shm();

        this.init();
    }

    set db(db) {
        this._db = db;
    }

    get db() {
        return this._db;
    }

    set name(name) {
        this._name = name;
    }

    get name() {
        return this._name
    }

    set blocks(blocks) {
        this._blocks = blocks;
    }

    get blocks() {
        return this._blocks;
    }

    set blockSize(blockSize) {
        this._blockSize = blockSize;
    }

    get blockSize() {
        return this._blockSize;
    }

    init() {
        this.db.open(this.name, this.blockSize, this.blocks);
    }

    close() {
        this.db.close();
    }

    size() {
        return this.db.size();
    }

    keys() {
        return this.db.keys();

    }

    get(key) {
        return this.db.get(key);
    }

    del(key) {
        return this.db.del(key);
        
    }

    put(key, value) {
        return this.db.put(key, value);
    }
}

module.exports = SharedMemory;