//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007-2016 musikcube team
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the author nor the names of other contributors may
//      be used to endorse or promote products derived from this software
//      without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "OverlayBase.h"
#include "TextInput.h"

namespace cursespp {
    class InputOverlay :
        public OverlayBase,
        public sigslot::has_slots<>
#if (__clang_major__ == 7 && __clang_minor__ == 3)
        , public std::enable_shared_from_this<InputOverlay>
#endif
    {
        public:
            using InputAcceptedCallback = std::function<void(const std::string&)>;

            InputOverlay();
            virtual ~InputOverlay();

            InputOverlay& SetTitle(const std::string& title);
            InputOverlay& SetText(const std::string& text);
            InputOverlay& SetInputAcceptedCallback(InputAcceptedCallback cb);
            InputOverlay& SetWidth(int width);
            InputOverlay& SetInputMode(IInput::InputMode mode);

            virtual void Layout();
            virtual bool KeyPress(const std::string& key);

        protected:
            virtual void OnVisibilityChanged(bool visible);
            virtual void OnInputEnterPressed(TextInput* input);
            virtual void OnInputKeyPress(TextInput* input, std::string key);

        private:
            void Redraw();
            void RecalculateSize();

            std::string title, text;
            int x, y;
            int width, height;
            int setWidth;
            std::shared_ptr<TextInput> textInput;
            InputAcceptedCallback inputAcceptedCallback;
    };
}