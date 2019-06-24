'use strict';

const { Shm } = require('bindings')('shm');

class SharedMemory {
    constructor(opts) {
        this.db = new Shm();
    }

    set db(db) {
        this._db = db;
    }

    get db() {
        return this._db;
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