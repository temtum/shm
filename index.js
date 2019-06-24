'use strict';

const { Shm } = require('bindings')('shm');

class SharedMemory {
    constructor() {
        this.db = new Shm();
    }

    set db(db) {
        this._db = db;
    }

    get db() {
        return this._db;
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